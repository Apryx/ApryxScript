package statement;

import context.ApryxVariable;
import context.Context;

public class IdentifierExpression extends Expression{
	
	private String name;
	
	public IdentifierExpression(String name){
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

	@Override
	public void check(Context context) {
		ApryxVariable v = context.getVariableByName(name);
		if(v == null)
			throw new RuntimeException("Variable not found");
	}
}
