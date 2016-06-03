package statement;

public class LookupExpression extends Expression{
	
	protected Expression rhs,lhs;
	
	public LookupExpression(Expression lhs, Expression rhs) {
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
		builder.append('.');
		builder.append(rhs.toJSString());
		
		return builder.toString();
	}
}
