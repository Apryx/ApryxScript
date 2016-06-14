package statement;

import context.Type;

public class IdentifierExpression extends Expression{
	
	private String name;
	
	public IdentifierExpression(String name){
		super(Type.UNKNOWN);
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}

	@Override
	public String toJSString() {
		return name;
	}
}
