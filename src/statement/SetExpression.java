package statement;

import context.Type;

public class SetExpression extends Expression{
	
	protected Expression rhs,lhs;
	
	public SetExpression(Expression lhs, Expression rhs) {
		super(Type.UNKNOWN); // TODO check whether these have the same type (during typechecking ofcourse)
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
		builder.append('='); 
		builder.append(rhs.toJSString());
		
		return builder.toString();
	}
}
