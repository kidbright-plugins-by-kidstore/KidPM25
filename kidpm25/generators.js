Blockly.JavaScript['kidpm25_read'] = function(block) {
	var dropdown_size = block.getFieldValue('size');
	var code = 'DEV_I2C1.KidPM25(0, 0x25).read(' + dropdown_size + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
