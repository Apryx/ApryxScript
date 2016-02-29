package statement;

import ast.ApryxClass;
import ast.Variable;
import language.Language;
import tokens.UndefinedReferenceException;

public class IdentifierExpression extends Expression{
	
	public static final String XML_STRING = "<get name=\"%s\" type=\"%s\" />";

	private String name;
	
	public IdentifierExpression(String name, String type) {
		super(type);
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public String toXML(){
		return String.format(XML_STRING, name, type);
	}
	
	@Override
	public void typeCheck(CodeBlock context) {
		
		//if the type is unknown, try to find the type
		//it must be a class now, because variables need to be defined in order!
		if(this.getType().equals(Language.TYPE_UNKNOWN)){
			Variable v = context.getVariableByName(name, false);
			
			if(v == null){
				ApryxClass c = context.getClassByName(name, false);
				
				if(c == null)
					throw new UndefinedReferenceException(name);
				else
					type = c.getName();
			}
			else
				type = v.getType();
		}
	}

}
