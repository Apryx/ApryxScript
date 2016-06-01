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

}
