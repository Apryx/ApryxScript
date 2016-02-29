package statement;

public abstract class Statement {
	public abstract String toXML();
	public abstract void typeCheck(CodeBlock context);
}
