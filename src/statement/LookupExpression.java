package statement;

import context.Type;

public class LookupExpression extends Expression{
	
	protected Expression rhs,lhs;
	
	public LookupExpression(Expression lhs, Expression rhs) {
		super(Type.UNKNOWN); //TODO reminder: In the check the context for the next check will be different!
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
