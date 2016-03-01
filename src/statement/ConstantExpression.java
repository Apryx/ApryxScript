package statement;

import ast.Type;

public class ConstantExpression extends Expression{
	
	private String value;
	
	public ConstantExpression(Type type, String value){
		super(type);
		this.value = value;
	}
	
	public String getValue() {
		return value;
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		builder.append("<constant type=\"");
		builder.append(type);
		builder.append("\">");
		
		builder.append(value);
		
		builder.append("</constant>");
		
		return builder.toString();
	}

	@Override
	public void typeCheck(Context context) {
		//TODO look at this, might be useful
	}
}
