# FILE AUTOMATICALLY GENERATED FROM /home/w1ngd1nga5ter/.vscode/.cache/paru/clone/zsh-zim-git/pkg/zsh-zim-git/usr/lib/zim/templates/.zimrc
# EDIT THE SOURCE FILE AND THEN RUN zimfw build. DO NOT DIRECTLY EDIT THIS FILE!

if [[ -e ${ZIM_CONFIG_FILE:-${ZDOTDIR:-${HOME}}/.zimrc} ]] zimfw() { source "/usr/lib/zim/zimfw.zsh" "${@}" }
fpath=("/usr/lib/zim/modules/git/functions" "/usr/lib/zim/modules/utility/functions" "/usr/lib/zim/modules/duration-info/functions" "/usr/lib/zim/modules/git-info/functions" "/usr/lib/zim/modules/zsh-completions/src" "/usr/lib/zim/modules/completion/functions" ${fpath})
autoload -Uz -- git-alias-lookup git-branch-current git-branch-delete-interactive git-branch-remote-tracking git-dir git-ignore-add git-root git-stash-clear-interactive git-stash-recover git-submodule-move git-submodule-remove mkcd mkpw duration-info-precmd duration-info-preexec coalesce git-action git-info
source "/usr/lib/zim/modules/environment/init.zsh"
source "/usr/lib/zim/modules/git/init.zsh"
source "/usr/lib/zim/modules/input/init.zsh"
source "/usr/lib/zim/modules/termtitle/init.zsh"
source "/usr/lib/zim/modules/utility/init.zsh"
source "/usr/lib/zim/modules/duration-info/init.zsh"
source "/usr/lib/zim/modules/asciiship/asciiship.zsh-theme"
source "/usr/lib/zim/modules/completion/init.zsh"
source "/usr/lib/zim/modules/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh"
source "/usr/lib/zim/modules/zsh-history-substring-search/zsh-history-substring-search.zsh"
source "/usr/lib/zim/modules/zsh-autosuggestions/zsh-autosuggestions.zsh"
