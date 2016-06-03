package statement;

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
}
