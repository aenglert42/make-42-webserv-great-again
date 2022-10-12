# make-42-webserv-great-again

## manual testing

### via terminal command line

#### curl

curl -X POST -H "Content-Type: plain/text" --data "BODY IS HERE write something shorter or longer than body limit" http://localhost:8080/new_file.txt

curl --resolve webserv.com:80:127.0.0.1 http://webserv.com/
(Port 80 is deafault and therefore not needed)

curl --resolve www.webserv.com:8080:127.0.0.1 http://www.webserv.com:8080


#### nc

echo "GET / HTTP/1.1\r\nHost: webserv\r\n\r\n" | nc localhost 8080

### using postman

## siege

siege -b http://localhost:8080/empty.html

### install brew

https://brew.sh/

(https://42born2code.slack.com/archives/C024QR1HT62/p1645537433618059)
if you wanna install brew in goinfre instead of your home drive (because it takes a lot of storage, even more if you install some tools) you can use this command:
rm -rf $HOME/.brew && rm -rf $HOME/goinfre/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
this command will also remove your current brew packages if you just wanna move it to goinfre you can use this command:
mv $HOME/.brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
the second one is not tested.
After installing always restart your terminal and run
brew --version
which brew
the second one should show something like this:
/Users/jsiller/goinfre/.brew/bin/brew
with 'jsiller' being replaced by your username

### install siege

### install xcode
