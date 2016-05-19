package statement;

public class OperatorExpression extends Expression{

	protected Expression rhs,lhs;
	
	public OperatorExpression(Expression lhs, Expression rhs) {
		super(lhs.getType());
	}
	
	public Expression getRhs() {
		return rhs;
	}
	
	public Expression getLhs() {
		return lhs;
	}

}
