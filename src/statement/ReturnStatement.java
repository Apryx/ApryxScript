package statement;

import context.Context;

public class ReturnStatement implements Statement{
	
	private Expression expression;
	
	public ReturnStatement(Expression exp){
		this.expression = exp;
	}

	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		builder.append("return ");
		builder.append(expression.toJSString());
		builder.append(';');
		
		return builder.toString();
	}
	
	@Override
	public void checkType(Context context) {
		//TODO typecheck the return statement stuff
	}

}
