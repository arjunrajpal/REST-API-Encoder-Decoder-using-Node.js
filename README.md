# REST API
General
This respository contains a REST API implmented in Node.js which recives data from an HTML/CSS file using AJAX request, modifies it and sends the modified data to a C++ program for encoding/decoding purpose.
The output received from the program is converted into JSON format and sent back the same HTML/CSS page.

STEPS FOR EXECUTING

-	Download latest version of Node.js installable archive file from Node.js Downloads. At the time of writing this tutorial, 	following are the versions available on different OS.
- OS	Archive name
- Windows	node-v0.12.0-x64.msi
- Linux	node-v0.12.0-linux-x86.tar.gz
- Mac	node-v0.12.0-darwin-x86.tar.gz
- SunOS	node-v0.12.0-sunos-x86.tar.gz

Based on your OS architecture, download and extract the archive node-v0.12.0-osname.tar.gz into /tmp, and then finally move extracted files into /usr/local/nodejs directory. For example-
  $ sudo apt-get install nodejs
  Add /usr/local/nodejs/bin to the PATH environment variable.

OS	Output
- Linux	export PATH=$PATH:/usr/local/nodejs/bin
- Mac	export PATH=$PATH:/usr/local/nodejs/bin
- FreeBSD	export PATH=$PATH:/usr/local/nodejs/bin

Installation on Windows
- Use the MSI file and follow the prompts to install the Node.js. By default, the installer uses the Node.js distribution in C:\Program Files\nodejs. The installer should set the C:\Program Files\nodejs\bin directory in window's PATH environment variable. Restart any open command prompts for the change to take effect.


INSTALLATION OF REQUIRED MODULES
- express
- body-parser
- child_process
- fs

eg: npm install module_name

AFTER INSTALLATION
- Download all the files in the same directory.
- Go to that directory through command line.
- Execute the .js file using command - "node sample.js"


