package statement;

public abstract class Expression {
	
	protected String type;
	
	public Expression(String type){
		this.type = type;
	}
	
	public String getType() {
		return type;
	}
	
	public abstract String toXML();
}
