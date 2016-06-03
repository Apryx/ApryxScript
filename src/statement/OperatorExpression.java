package statement;

public class OperatorExpression extends Expression{

	protected Expression rhs,lhs;
	
	public OperatorExpression(Expression lhs, Expression rhs) {
		this.lhs = lhs;
		this.rhs = rhs;
	}
	
	public Expression getRhs() {
		return rhs;
	}
	
	public Expression getLhs() {
		return lhs;
	}
	
	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		builder.append(lhs.toJSString());
		builder.append('+'); //TODO fix the right operator :")
		builder.append(rhs.toJSString());
		
		return builder.toString();
	}

}
