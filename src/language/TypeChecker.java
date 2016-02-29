package language;

import statement.CodeBlock;

public class TypeChecker {

	public TypeChecker() {

	}

	public void check(CodeBlock block) {
		// check block with no parent context
		block.typeCheck();
	}
}
