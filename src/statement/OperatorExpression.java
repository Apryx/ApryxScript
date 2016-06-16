package statement;

import context.Type;

public class OperatorExpression extends Expression{

	protected Expression rhs,lhs;
	private String operator;//This should not be String
	
	public OperatorExpression(Expression lhs, Expression rhs, String operator) {
		super(Type.UNKNOWN); //TODO in checker, search for the right overloads
		this.lhs = lhs;
		this.rhs = rhs;
		this.operator = operator;
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
		builder.append(operator); //TODO fix the right operator :")
		builder.append(rhs.toJSString());
		
		return builder.toString();
	}

}
