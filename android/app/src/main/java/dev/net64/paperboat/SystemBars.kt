package dev.net64.paperboat

import android.view.View
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

/**
 * Keeps content clear of the status bar, navigation bar and cutout, on top of
 * whatever padding it already has. From API 35 every window is laid out edge to
 * edge and the old opt-outs are ignored, which put the launcher's Choose ROM
 * button behind the navigation bar. The game instead hides the bars outright;
 * see [MainActivity].
 */
fun View.padForSystemBars() {
    val left = paddingLeft
    val top = paddingTop
    val right = paddingRight
    val bottom = paddingBottom

    ViewCompat.setOnApplyWindowInsetsListener(this) { view, insets ->
        val bars = insets.getInsets(
            WindowInsetsCompat.Type.systemBars() or WindowInsetsCompat.Type.displayCutout()
        )
        view.setPadding(left + bars.left, top + bars.top, right + bars.right, bottom + bars.bottom)
        insets
    }
}
