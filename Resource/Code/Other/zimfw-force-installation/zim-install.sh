print -n '[WARN] IT IS RECOMMENDED TO INSTALL ZSH-ZIM WITH YOUR PACKAGE MANAGER. ENTER q TO QUIT, OR CONTINUE.'
read ch
if [[ "$ch" == 'q' ]] ; then
    exit
fi
sudo cp -r files/* /
cp .zshrc ~/
cp .zimrc ~/
sudo cp .zshrc /root
sudo cp .zimrc /root
echo Done. Please enter root and run 'zimfw install' manually.
