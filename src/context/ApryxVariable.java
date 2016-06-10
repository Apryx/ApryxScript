package context;

import statement.Expression;

public class ApryxVariable {
	
	private String name;
	private Expression defaultValue;
	
	public ApryxVariable(String name){
		this.name = name;
	}
	
	public ApryxVariable(String name, Expression defaultValue){
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
