package statement;

public class SetExpression extends Expression{
	
	protected Expression rhs,lhs;
	
	public SetExpression(Expression lhs, Expression rhs) {
		this.lhs = lhs;
		this.rhs = rhs;
	}
	
	public Expression getRhs() {
		return rhs;
	}
	
	public Expression getLhs() {
		return lhs;
	}
}
