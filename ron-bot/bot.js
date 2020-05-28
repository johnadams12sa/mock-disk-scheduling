var Discord = require('discord.io');
var logger = require('winston');
var auth = require('./auth.json');

//Configure logger settings
logger.remove(logger.transports.Console);
logger.add(new logger.transports.Console, {
	colorize: true
});
logger.level = 'debug';

//Initialize Discord Bot
var ron_bot = new Discord.Client({
	token: auth.token,
	autorun: true
});

ron_bot.on('ready', function (evt) {
	logger.info('Connected');
	logger.info('Logged in as: ');
	logger.info(ron_bot.username + ' - (' + ron_bot.id + ')');
});
ron_bot.on('message', function (user, userID, channelID, message, evt){
	//our bot needs to know if it will execute a command
	//it will listen for messages that will start with `!`
	if(message.substring(0,1) == '!') {
		var args = message.substring(1).split(' ');
		var cmd = args[0];

		args = args.splice(1);
		switch(cmd) {
			//!ping
			case 'ping':
			bot.sendMessage({
				to: channelID,
				message: 'Pong!'
			});
			break;
			
			case 'greet':
			bot.sendMessage({
				to: channelID,
				message: 'Wassup homes.'
			});
			break;
			
			case 'play':
			playMusic();
		//Add more later
		}
	}
});
