package statement;

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

}
