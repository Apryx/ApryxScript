package statement;

public class OperatorExpression extends Expression{

	public static final String OPERATION_ADD = "add";
	public static final String OPERATION_SUBTRACT = "subtract";
	public static final String OPERATION_DEVIDE = "devide";
	public static final String OPERATION_MULTIPLY = "multiply";

	private Expression lhs, rhs;
	private String opp;
	
	public OperatorExpression(String operation, Expression lhs, Expression rhs){
		super(lhs.getType());
		//TODO fix type for operator
		this.lhs = lhs;
		this.rhs = rhs;
		opp = operation;
	}

	@Override
	public String toXML() {
		StringBuilder builder = new StringBuilder();
		
		builder.append("<");
		builder.append(opp);
		builder.append(" type=\"");
		builder.append(type);
		builder.append("\">");
		
		builder.append(lhs.toXML());
		builder.append(rhs.toXML());
		
		builder.append("</");
		builder.append(opp);
		builder.append(">");
		
		return builder.toString();
	}
	
	

}
