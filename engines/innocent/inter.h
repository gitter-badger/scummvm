#ifndef INNOCENT_INTER_H
#define INNOCENT_INTER_H

#include <memory>

#include "common/util.h"
#include "config.h"

namespace Innocent {

class Logic;
class Opcode;
class Engine;
class Resources;
class Graphics;

#define UNIMPLEMENTED { error("type conversion unimplemented"); }

enum OpcodeMode {
	kCodeInitial = 0,
	kCodeNewRoom = 1,
	kCodeNewBlock = 8
};

enum Status {
	kReturned = 0,
	kInvalidOpcode = 1
};

class Argument {
public:
	Argument(byte *ptr) : _ptr(ptr) {}
	virtual ~Argument() {}
	virtual operator uint16() const UNIMPLEMENTED
	virtual operator byte() const UNIMPLEMENTED
	virtual Argument operator=(byte b) UNIMPLEMENTED
	virtual Argument operator=(uint16 b) UNIMPLEMENTED
	byte *_ptr; // for debug
};

class Interpreter {
public:
	Interpreter(Logic *l, byte *base);

	void init();

	/**
	 * Run bytecode.
	 * @param code a Common::ReadStream pointing to code. The interpreter takes ownership of it.
	 * @param mode interpreting mode.
	 */
	Status run(uint16 offset, OpcodeMode mode);

	Argument *getArgument();

	friend class Opcode;

	template <int opcode>
	void opcodeHandler(Argument *args[]);

	template <int N>
	void init_opcodes();

	typedef void (Interpreter::*OpcodeHandler)(Argument *args[]);
	OpcodeHandler _handlers[256];
	static const uint8 _argumentsCounts[];

	Logic *_logic;

private:
	Status run();
	byte *_base;
	byte *_code;
	uint16 _mode;

	Argument *readImmediateArg();
	Argument *readMainWordArg();
	Argument *readMainByteArg();
	Argument *readLocalArg();

	void failedCondition();
	void endIf();
	void goBack();

	uint16 _failedCondition;
	bool _return;
	
	Engine *_engine;
	Resources *_resources;
	Graphics *_graphics;
};

} // End of namespace Innocent

#endif // INNOCENT_INTER_H
