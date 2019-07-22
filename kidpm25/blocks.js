Blockly.Blocks['kidpm25_read'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDPM25_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "size",
				"options": [
					[ "PM2.5", "25" ],
					[ "PM1.0", "10" ],
					[ "PM10", "100" ]
				]
			}],
			"output": "Number",
			"colour": 135,
			"tooltip": Blockly.Msg.KIDPM25_READ_TOOLTIP,
			"helpUrl": "https://www.ioxhop.com/"
		});
	}
};
