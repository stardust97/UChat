const http = require('http');

// 定义要发送的数据  
const requestData = {
  email: 'x641765169@163.com',
};
// 转换为JSON字符串  
const jsonData = JSON.stringify(requestData);  
  
// 发送POST请求  
fetch('http://127.0.0.1:8889/login/get_verifycode', {  
  method: 'POST', 
  headers: {  
    'Content-Type': 'application/json', // 告诉服务器我们发送的是JSON格式的数据  
  },  
  body: jsonData, // 发送的数据  
})  
.then(response => {  
  if (!response.ok) {  
    throw new Error('Network response was not ok');  
  }  
  return response.json(); // 解析JSON数据  
})  
.then(data => {  
  console.log(data); // 在这里处理接收到的数据  
})  
.catch(error => {  
  console.error('There has been a problem with your fetch operation:', error);  
});