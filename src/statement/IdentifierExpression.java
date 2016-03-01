package statement;

import ast.Type;

public class IdentifierExpression extends Expression{
	
	public static final String XML_STRING = "<get name=\"%s\" type=\"%s\" />";

	private String name;
	private Expression invokationContext;
	
	public IdentifierExpression(String name, Type type) {
		super(type);
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public Expression getInvokationContext() {
		return invokationContext;
	}
	
	public void setInvokationContext(Expression invokationContext) {
		this.invokationContext = invokationContext;
	}
	
	public String toXML(){
		return String.format(XML_STRING, name, type.toString());
	}
	
	@Override
	public void typeCheck(Context context) {
		//TODO STATIC STUFF
		
		//if the type is unknown, try to find the type
		//it must be a class now, because variables need to be defined in order!
		if(this.getType().isUnknown()){
			type = context.resolveType(type);
			
			//TODO error handling
		}
	}

}
