package context;

import statement.Expression;

public class FunctionArgument {
	
	private String name;
	private Expression defaultValue;
	
	public FunctionArgument(String name){
		this.name = name;
	}
	
	public FunctionArgument(String name, Expression defaultValue){
		this.name = name;
		this.defaultValue = defaultValue;
	}
	
	public Expression getDefaultValue() {
		return defaultValue;
	}
	
	public String getName() {
		return name;
	}
	
	public boolean hasDefaultValue(){
		return this.defaultValue != null;
	}
}
