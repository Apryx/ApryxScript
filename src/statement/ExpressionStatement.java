package statement;

import context.Context;

public class ExpressionStatement implements Statement{
	
	private Expression expression;
	
	public ExpressionStatement(Expression expression){
		this.expression = expression;
	}
	
	public Expression getExpression() {
		return expression;
	}
	
	public void setExpression(Expression expression) {
		this.expression = expression;
	}

	@Override
	public String toJSString() {
		//No stringbuilder needed, java compiler does that for us here :D
		return expression.toJSString() + ";";
	}

	@Override
	public void check(Context context) {
		expression.check(context);
	}
}
