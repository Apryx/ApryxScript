package language;

import statement.Context;

public class TypeChecker {

	public TypeChecker() {

	}

	public void check(Context block) {
		// check block with no parent context
		block.typeCheck();
	}
}
