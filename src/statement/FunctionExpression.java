package statement;

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

}
