package statement;

import context.Context;

public class ConstantExpression extends Expression{
	
	public enum Type{
		STRING, INTEGER, FLOAT, DOUBLE
	}
	
	private String value;
	private Type type;
	
	public ConstantExpression(String value, Type type){
		this.value = value;
		this.type = type;
	}
	
	public String getValue() {
		return value;
	}
	
	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();

		if(type == Type.STRING)
			builder.append('"');
		builder.append(value);
		
		if(type == Type.STRING)
			builder.append('"');
		
		return builder.toString();
	}

	@Override
	public void check(Context context) {
		//Do nothing, the type is always correct for a constant
	}
}
