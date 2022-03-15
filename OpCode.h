#pragma once

enum OpCode {
	OP_NOOP = 0x00,
	OP_PUSHCONST = 0x01,

	//Mathematical instructions
	OP_ADDSTACK = 0x02,
	OP_SUBSTACK = 0x03,
	OP_MULSTACK = 0x04,

	OP_PRINTSTACK = 0x05,
	OP_HALT = 0xFF
};
