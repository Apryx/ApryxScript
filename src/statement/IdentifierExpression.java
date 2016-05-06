package statement;

public class IdentifierExpression extends Expression{
	
	private String name;
	
	public IdentifierExpression(String name, Type type){
		super(type);
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
}