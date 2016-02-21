package statement;

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

}
