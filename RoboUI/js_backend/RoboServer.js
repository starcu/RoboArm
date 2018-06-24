var http = require('http');
var os = require('os');
var url = require('url');
var rcli = require('./RoboCLIWrapper');

http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    
	var q = url.parse(req.url, true).query;
    var txt = q.axis;

    if (txt == "x")
	{
		res.write("x = ");
		res.write(rcli.gyro_x());
	}
	else if(txt == "y")
	{
		res.write("y = ");
		res.write(rcli.gyro_y());
	}
	else if(txt == "z")
	{
		res.write("z = ");
		res.write(rcli.gyro_z());
	}
	else
	{
		res.write("Hello from world :)");
	}

    res.end();
}).listen(8080); 