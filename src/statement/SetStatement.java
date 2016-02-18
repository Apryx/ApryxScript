package statement;

public class SetStatement extends Statement {
	
	private String name;
	private Expression value;
	
	public SetStatement(String name, Expression value){
		this.name = name;
		this.value = value;
	}
}
