#pragma once

class CObject;

class CComponent
{
public:
    CComponent() = default;
    virtual ~CComponent() = default;

public:
    virtual void BeginPlay()		abstract {}
    virtual void TickComponent()	abstract {}
    virtual void Release()			abstract {}

public:
    void	 Set_Owner(CObject* _Owner) { m_Owner = _Owner; }
    CObject* Get_Owner() { return m_Owner; }

private:
    CObject* m_Owner = nullptr;
};

