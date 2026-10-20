#pragma once
#ifdef ENABLE_SCRIPTING

#include <functional>
#include <string>
#include <utility>
#include <vector>

// Things the player allows or denies once, such as a mod going online. Answers are kept in permissions.json next to
// the game.
namespace Permissions {

enum class State {
    Pending,
    Allowed,
    Denied
};

struct PromptDef {
    std::string title;
    std::string message;
};

// Sets the prompt shown for key. Registering a key again replaces its prompt.
void Register(const std::string& key, PromptDef prompt);

// The player's answer for key, Pending when they haven't been asked.
State Get(const std::string& key);

// Every answer the player gave, by key, for the settings page.
std::vector<std::pair<std::string, State>> All();
// Changes an answer from the settings page. Pending forgets it, so the player is asked again.
void SetAnswer(const std::string& key, State state);
// The prompt registered for key, or nullptr.
const PromptDef* Prompt(const std::string& key);

// Asks the player when the key is still Pending. The callbacks run after they answer; both may be empty.
void Request(const std::string& key, std::function<void()> onAllow = nullptr, std::function<void()> onDeny = nullptr);

} // namespace Permissions
#endif
