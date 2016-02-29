package ast;

import language.Language;
import statement.CodeBlock;
import statement.Expression;
import tokens.UnknownTypeException;

public class Variable {
	
	private String name, type;
	private boolean argument;
	private Expression initialValue;

	public Variable(String name, String type){
		this(name, type, false);
	}
	
	public Variable(String name, String type, boolean argument){
		this.name = name;
		this.type = type;
		this.argument = argument;
	}
	
	public void typeCheck(CodeBlock block){
		//TODO actually check the type for this variable!
		if(initialValue != null){
			initialValue.typeCheck(block);
			
			if(type.equals(Language.TYPE_UNKNOWN)){
				type = initialValue.getType();
			}
		}
		
		if(type.equals(Language.TYPE_UNKNOWN)){
			throw new UnknownTypeException(name);
		}
	}
	
	public Expression getInitialValue() {
		return initialValue;
	}
	
	public void setInitialValue(Expression initialValue) {
		this.initialValue = initialValue;
	}
	
	public String getType() {
		return type;
	}
	
	public String getName() {
		return name;
	}
	
	public boolean isArgument() {
		return argument;
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		builder.append(String.format("<%s name=\"%s\" type=\"%s\" >", argument ? "argument" : "variable", name, type));
		if(initialValue != null)
			builder.append(initialValue.toXML());
		builder.append(argument ? "</argument>" : "</variable>");
		
		return builder.toString();
	}
}
