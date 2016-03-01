package ast;

import statement.Context;
import statement.Expression;
import tokens.UnknownTypeException;

public class Variable {
	
	private String name;
	private Type type;
	private boolean argument;
	private Expression initialValue;

	public Variable(String name, Type type){
		this(name, type, false);
	}
	
	public Variable(String name, Type type, boolean argument){
		this.name = name;
		this.type = type;
		this.argument = argument;
	}
	
	public void typeCheck(Context context){
		//TODO actually check the type for this variable!
		if(initialValue != null){
			initialValue.typeCheck(context);
			
			if(type.isUnknown()){
				type = initialValue.getType();
			}
		}
		
		if(type.isUnknown()){
			//TODO do the rest of the typechecking because we don't know this yet ! :D
			
			type = context.resolveType(type);
			
			if(type.isUnknown())
				throw new UnknownTypeException(name);
		}
	}
	
	public Expression getInitialValue() {
		return initialValue;
	}
	
	public void setInitialValue(Expression initialValue) {
		this.initialValue = initialValue;
	}
	
	public Type getType() {
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
