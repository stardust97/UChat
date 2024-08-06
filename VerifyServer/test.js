const nodemailer = require('nodemailer');  
  
async function sendMail() {  
    let transport = nodemailer.createTransport({
        host: 'smtp.qq.com',
        port: 465,
        secure: true,
        auth: {
            // user: config_module.email_user, // 发送方邮箱地址
            user: '641765169@qq.com', // 发送方邮箱地址
            pass: 'fkahqwwaukebbcjf' // 邮箱授权码或者密码
            // pass: config_module.email_pass // 邮箱授权码或者密码
        }
    });
  
    let mailOptions = {  
        from: '641765169@qq.com', // 发件人地址  
        to: "x641765169@163.com", // 收件人列表，逗号分隔的字符串  
        subject: "Hello ✔", // 主题行  
        text: "Hello world?", // 纯文本正文  
        html: "<b>Hello world?</b>" // HTML正文  
    };  
  
    // 发送邮件  
    let response = await transport.sendMail(mailOptions);  
  
    console.log('Message sent: %s', response.messageId);  
}  
  
sendMail().catch(console.error);