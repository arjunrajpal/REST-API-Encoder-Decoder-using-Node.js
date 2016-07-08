var express=require('express');
var app=express();
var bodyParser=require('body-parser');
var fs=require('fs');
var child_process=require('child_process');

var urlencodedParser=bodyParser.urlencoded({extended:false});

app.use(express.static("public"));
/*var http=require('http');
http.createServer(function(request,response)
{
                  response.writeHead(400,{'Content-Type':'text/html'});
                  response.end('hellodshdsg');
}).listen(8080);
*/

app.get('/',function(request,response)
        {
        response.sendFile(__dirname+"/HTML_PAGE.html");
        });

app.post('/postData',urlencodedParser,function(request,response)
         {
         var body=request.body;
         console.log(body);
         console.log(JSON.stringify(request.body));
         console.log("hel");
         //alert('he');
         var smsc=body.smsc;
         var position=smsc.indexOf(".",0);
         var length=smsc.length;
         if(position!=-1)
         {
         var smsc=smsc.substring(0,position);
         }
         
         
         var receiver=body.receiver;
         position=receiver.indexOf(".",0);
         if(position!=-1)
         {
         var receiver=receiver.substring(0,position);
         }
         
         
         var size=body.size;
         var mclass=body.mclass;
         var receipt=body.receipt;
         var validity=body.validity;
         var val=body.val;
         var origmess1=body.origmess1;
         var origmess2=body.origmess2;
         
         console.log(body.origmess1);
         console.log(body.origmess2);
         
         if(origmess2=="Write Text")
         {
         if(receipt=='on')
         {
         receipt='1';       //Receipt to 1 for on status
         }
         else
         {
         receipt='0';        //0 for off
         }
         
         
         
         
         if(validity=='on')
         {
         validity='1';      //Validity to 1 for on status
         }
         else
         {
         validity='0';       //0 for off
         }
         
         
         
         
         if(smsc !== undefined)
         {
         if(validity=='0')  //checks for validity
         {
         var data=smsc+'\n'+receiver+'\n'+size+'\n'+mclass+'\n'+receipt+'\n'+validity+'\n'+origmess1;
         }
         else   //validity period included
         {                     data=smsc+'\n'+receiver+'\n'+size+'\n'+mclass+'\n'+receipt+'\n'+validity+'\n'+val+'\n'+origmess1;              
         }
         fs.writeFile('test.txt',data,'utf8'); //writes credentials in a text file
         
         
         var child=child_process.exec("./enc_with_file");  //executes the program in the directory
         var resp="";
         
         child.stdout.on('data',function(data){
                         resp+=data.toString()      //Store program output in resp
                         });
         
         child.stdout.on('end',function(){
                         var output={data:resp};
                         //if(resp!=NULL)
                         console.log("Output"+resp);
                         response.end(resp);
                         });
         
         }
         }
         
         else
         {
         var data=origmess2;
         fs.writeFile('test2.txt',data,'utf8'); //writes message to be decoded in text2.txt
         
         var child=child_process.exec("./dec_with_file"); //executes the program in the directory
         resp="";
         
         child.stdout.on('data',function(data){
                         resp+=data.toString()
                         });
         child.stdout.on('end',function(){
                         var output={data:resp};
                         //if(resp!=NULL)
                         console.log("Output"+resp);
                         response.end(resp);
                         });
         }

         });
         
var server=app.listen(8080,function()
                      {
                      var address=server.address().address;
                      var port=server.address().port;
                      });

console.log("Server running");