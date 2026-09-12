package dev.net64.paperboat

import android.content.Context
import android.net.Uri
import android.provider.DocumentsContract
import android.util.Log
import java.io.File
import java.io.FileOutputStream
import java.util.zip.ZipEntry
import java.util.zip.ZipInputStream
import java.util.zip.ZipOutputStream

/**
 * The game's save files: `saves/fileN.json`, one per slot (see
 * src/port/save/SaveManager.cpp). The `default.sav` the game also writes is the
 * N64 SRAM image, not a per-slot save, so it is deliberately not listed.
 *
 * Matched by extension, not name, so a slot added upstream needs no change here.
 */
object SaveStore {

    private const val TAG = "SaveStore"
    private const val COPY_BUFFER = 1 shl 16

    const val BUNDLE_NAME = "paperboat-saves.zip"

    data class Save(val file: File) {
        val label: String
            get() = file.name.removeSuffix(".json")
                .removePrefix("file")
                .toIntOrNull()
                ?.let { "File ${it + 1}" }
                ?: file.name
    }

    fun savesDir(context: Context): File =
        File(GameAssets.gameDir(context), "saves").also { it.mkdirs() }

    fun list(context: Context): List<Save> =
        (savesDir(context).listFiles() ?: emptyArray())
            .filter { it.isFile && it.name.endsWith(".json", ignoreCase = true) }
            .sortedBy { it.name }
            .map { Save(it) }

    fun delete(save: Save): String? =
        if (save.file.delete()) null else "Could not delete ${save.label}."

    fun export(context: Context, save: Save, destination: Uri): String? = runOrReport("export") {
        context.contentResolver.openOutputStream(destination).use { output ->
            requireNotNull(output) { "The document provider did not open the destination." }
            save.file.inputStream().use { input -> input.copyTo(output, COPY_BUFFER) }
        }
    }

    fun exportAll(context: Context, destination: Uri): String? = runOrReport("export") {
        val saves = list(context)
        check(saves.isNotEmpty()) { "There are no saves to export yet." }

        context.contentResolver.openOutputStream(destination).use { output ->
            requireNotNull(output) { "The document provider did not open the destination." }
            ZipOutputStream(output.buffered()).use { zip ->
                for (save in saves) {
                    zip.putNextEntry(ZipEntry(save.file.name))
                    save.file.inputStream().use { input -> input.copyTo(zip, COPY_BUFFER) }
                    zip.closeEntry()
                }
            }
        }
    }

    /**
     * Restores a single save, or every save out of a zip written by
     * [exportAll]. Existing files of the same name are replaced.
     */
    fun import(context: Context, uri: Uri): String? {
        val displayName = queryDisplayName(context, uri) ?: return "Could not read the file's name."

        return when {
            displayName.endsWith(".zip", true) -> importBundle(context, uri)
            displayName.endsWith(".json", true) -> runOrReport("import") {
                context.contentResolver.openInputStream(uri).use { input ->
                    requireNotNull(input) { "The document provider did not open $displayName." }
                    FileOutputStream(File(savesDir(context), displayName)).use { output ->
                        input.copyTo(output, COPY_BUFFER)
                    }
                }
            }
            else -> "$displayName is not a save. Saves are .json files, or a .zip of them."
        }
    }

    private fun importBundle(context: Context, uri: Uri): String? = runOrReport("import") {
        val target = savesDir(context)
        var restored = 0

        context.contentResolver.openInputStream(uri).use { input ->
            requireNotNull(input) { "The document provider did not open the archive." }
            ZipInputStream(input.buffered()).use { zip ->
                while (true) {
                    val entry = zip.nextEntry ?: break
                    val name = File(entry.name).name

                    // Plain .json only: an archive from elsewhere could carry
                    // ../../ entries pointing out of the saves directory.
                    if (entry.isDirectory || !name.endsWith(".json", true)) {
                        zip.closeEntry()
                        continue
                    }

                    FileOutputStream(File(target, name)).use { output -> zip.copyTo(output, COPY_BUFFER) }
                    zip.closeEntry()
                    restored++
                }
            }
        }

        check(restored > 0) { "That archive has no save files in it." }
    }

    private fun runOrReport(verb: String, work: () -> Unit): String? = try {
        work()
        null
    } catch (error: Exception) {
        Log.e(TAG, "Save $verb failed", error)
        "Could not $verb: ${error.message ?: error}"
    }

    private fun queryDisplayName(context: Context, uri: Uri): String? =
        context.contentResolver.query(uri, arrayOf(DocumentsContract.Document.COLUMN_DISPLAY_NAME), null, null, null)
            ?.use { cursor -> if (cursor.moveToFirst()) cursor.getString(0) else null }
}
