package statement;

public class ConstantExpression extends Expression{
	
	private String value;
	
	public ConstantExpression(String type, String value){
		super(type);
		this.value = value;
	}
	
	public String getValue() {
		return value;
	}
}
