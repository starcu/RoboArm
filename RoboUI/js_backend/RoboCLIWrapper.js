const shell = require('shelljs');

readJsonFromCLI = function() {
    json = shell.exec('../build/RoboCLI/RoboCLI', {silent: true}); // {silent: true} -> return to variable, no output shown in console
    return json;
}

exports.gyro_x = function () {
	var json = readJsonFromCLI();
    var obj = JSON.parse(json);
    return String(obj.x);
}; 

exports.gyro_y = function () {
    var json = readJsonFromCLI();
    var obj = JSON.parse(json);
    return String(obj.y);
}; 

exports.gyro_z = function () {
    var json = readJsonFromCLI();
    var obj = JSON.parse(json);
    return String(obj.z);
};