const nodemailer = require('nodemailer');
const config_module = require("./config")

let transport = nodemailer.createTransport({
    host: config_module.server_host,
    port: config_module.port,
    secure: config_module.enable_ssl,
    auth: {
        user: config_module.email_user,
        pass: config_module.email_pass
    }
});

function SendMail(mailOptions_){
    return new Promise(function(resolve, reject){
        transport.sendMail(mailOptions_, function(error, info){
            if (error) {
                console.log(error);
                reject(error);
            } else {
                console.log('邮件已成功发送：' + info.response);
                resolve(info.response)
            }
        });
    })
   
}

module.exports.SendMail = SendMail