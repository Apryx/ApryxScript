package statement;

public class ReturnStatement extends Statement{
	
	private Expression exp;
	
	public ReturnStatement(Expression e){
		exp = e;
	}
	
	@Override
	public String toXML() {
		StringBuilder builder = new StringBuilder();
		
		builder.append("<return type=\"");
		
		builder.append(exp.getType());
		
		builder.append("\">");
		
		builder.append(exp.toXML());
		
		builder.append("</return>");
		
		return builder.toString();
	}
	
	@Override
	public void typeCheck(CodeBlock context) {
		// TODO implement typechecking return statement
		exp.typeCheck(context);
	}
}
