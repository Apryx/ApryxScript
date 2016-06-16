package statement;

import context.Type;

public class ConstantExpression extends Expression{
	
	private String value;
	
	public ConstantExpression(String value, Type type){
		super(type);
		this.value = value;
	}
	
	public String getValue() {
		return value;
	}
	
	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();

		if(getType().equals(Type.STRING))
			builder.append('"');
		builder.append(value);
		
		if(getType().equals(Type.STRING))
			builder.append('"');
		
		return builder.toString();
	}
}
