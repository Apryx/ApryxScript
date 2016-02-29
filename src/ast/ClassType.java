package ast;

public class ClassType extends Type{
	
	private ApryxClass cls;

	public ClassType(ApryxClass cls) {
		super(cls.getName());
	}
	
	@Override
	public boolean isInvokeable() {
		return false;
	}

	@Override
	public ApryxClass getApryxClass() {
		return cls;
	}
	
}
