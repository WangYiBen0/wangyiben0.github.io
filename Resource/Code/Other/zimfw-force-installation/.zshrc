# Created by newuser for 5.9

if ! [[ -v ZIM_HOME ]]; then
  export ZIM_HOME=/usr/lib/zim
  source "/usr/lib/zim/init.zsh"
fi

# To customize prompt, run `p10k configure` or edit ~/.p10k.zsh.
[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh

export PATH=$PATH:/home/w1ngd1nga5ter/.spicetify

[[ -s /etc/profile.d/autojump.sh ]] && source /etc/profile.d/autojump.sh

#fortune | cowsay | lolcat

# Auto-Warpify
[[ "$-" == *i* ]] && printf 'P$f{"hook": "SourcedRcFileForWarp", "value": { "shell": "zsh", "uname": "Linux" }}�' 
