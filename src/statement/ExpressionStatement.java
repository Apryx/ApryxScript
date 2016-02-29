package statement;

public class ExpressionStatement extends Statement{

	private Expression exp;
	
	public ExpressionStatement(Expression e){
		exp = e;
	}
	
	@Override
	public String toXML() {
		return exp.toXML();
	}

	@Override
	public void typeCheck(CodeBlock context) {
		exp.typeCheck(context);
	}
	
}
