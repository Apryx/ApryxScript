package statement;

import context.Context;
import context.Function;

public class FunctionExpression extends Expression{

	private Function function;
	
	public FunctionExpression(Function function){
		this.function = function;
	}
	
	@Override
	public String toJSString() {
		return function.toJSString();
	}

	@Override
	public void check(Context context) {
		//TODO the right typechecking
		function.getStatement().setParent(context);
		function.getStatement().check();
	}

}
