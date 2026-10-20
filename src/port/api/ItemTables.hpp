#pragma once

#include <string>

// Numbers of mod items for the save code. Unlike the C API, these work in every build, including those without
// scripting, so a save keeps the mod items it holds even where it can't show them.
namespace ItemTables {

// Number of the item id this session, giving it one the first time, preferred when that one is free. An id no loaded
// mod registers still gets a number, which reads as no item until the mod is back. -1 when the mod item range is
// full.
int Number(const std::string& id, int preferred, const std::string& owner);
// Id of a number handed out this session, or nullptr.
const std::string* IdOf(int number);
// Mod that registered the id, as last known.
std::string Owner(const std::string& id);
// True when a loaded mod registers the item.
bool IsRegistered(int number);

} // namespace ItemTables
