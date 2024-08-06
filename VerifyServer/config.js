
const fs = require('fs');
let config = JSON.parse(fs.readFileSync('config.json', 'utf8'));

// grpc settings
let bind_address = config.grpc_bind_address;
// email settings
let email_user = config.email.user;
let server_host = config.email.server_host;
let email_pass = config.email.pass;
let server_port = config.email.server_port;
let enable_ssl = config.email.enable_ssl;
// mysql settings
let mysql_host = config.mysql.host;
let mysql_port = config.mysql.port;
// redis settings
let redis_host = config.redis.host;
let redis_port = config.redis.port;
let redis_passwd = config.redis.passwd;

let code_prefix = "code_";

module.exports = {
  bind_address, email_pass, email_user, server_host, server_port,
  enable_ssl, mysql_host, mysql_port, redis_host, redis_port,
  redis_passwd, code_prefix
}
